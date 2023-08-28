/**********************************************************************************************************************
 * Bukhtagram                                                                                                         *
 *                                                                                                                    *
 * Author: Bukhta Mykyta                                                                                              *
 *                                                                                                                    *
 * Copyright ©2023 Bukhta Mykyta                                                                                      *
 *                                                                                                                    *
 * This software is distributed under the following license:                                                          *
 *                                                                                                                    *
 * 1. This code may not be modified, redistributed, or used to create derivative works.                               *
 * 2. Any use of this code for commercial purposes is prohibited without prior written permission of the author.      *
 * 3. The author is not liable for any damages caused by the use of this software.                                    *
 * 4. Copies of this license or references to it must be included in all copies or significant parts of the software. *
 *                                                                                                                    *
 * For permission for commercial use, contact the author at the following address: nikita.bukhta.dev@gmail.com.       *
 **********************************************************************************************************************                                                                                                                    *
 */

#include "ClientController.hpp"

#include "Logger.hpp"

#include <boost/function.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind/bind.hpp>

#include <array>
#include <vector>
#include <iostream>

namespace bukhtagram {
namespace mc {
namespace client {
namespace controllers {

ClientController::ClientController(std::weak_ptr<models::IClientModel> client_model)
    : m_client_model(client_model.lock())
{
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
}

ClientController::~ClientController(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";

    auto socket = m_client_model->socket().lock();
    socket->close();
}

void ClientController::run(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";

    start_read();
}

bool ClientController::connect_to(const std::string &address, uint16_t port) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
    boost::system::error_code error_code;
    auto socket = m_client_model->socket().lock();
    boost::asio::ip::tcp::endpoint server_endpoint(
        boost::asio::ip::address::from_string(address), port
    );
    socket->connect(server_endpoint, error_code);
    if (!handle_error(error_code)) {
        LOG_INFO << "connected!";
        return true;
    }

    LOG_ERROR << "Cannot to connect to the server";
    return false;
}

void ClientController::send_message(const std::string &message) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;
    LOG_INFO << "data size: " << message.size();

    auto socket = m_client_model->socket().lock();

    boost::function<void(const uint64_t, const boost::system::error_code&)> write_handler = boost::bind(&ClientController::handle_write, this, _1, _2);

    socket->async_write_some(
        boost::asio::buffer(message.data(), message.size()), [write_handler](const boost::system::error_code &error, const uint64_t bytes_transferred){
            write_handler(bytes_transferred, error);
    });
}

void ClientController::start_read(void) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";

    /* As we use async programming, the data should be destroyed at the end of the method.
       To escape the desctruction the buffer, we made this static + made optimization of method work :);
     */
    static std::array<char, STANDART_BUFFER_SIZE> buf;
    boost::system::error_code error;
    auto socket = m_client_model->socket().lock();

    boost::function<void(std::array<char, STANDART_BUFFER_SIZE>&, const uint64_t, const boost::system::error_code)> read_handler
        = boost::bind(&ClientController::handle_read, this, _1, _2, _3);

    socket->async_read_some(boost::asio::buffer(buf), [read_handler](const boost::system::error_code &error, const uint64_t bytes_transferred){
        read_handler(buf, bytes_transferred, error);
    });
}

// TODO: fix bug when server is closed;
bool ClientController::handle_error(const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;

    if (error.value() == boost::system::errc::success) {
        LOG_TRACE << "no errors handled";
        return false;
    }

    LOG_ERROR << error.what();
    return true;
}

void ClientController::handle_read(std::array<char, STANDART_BUFFER_SIZE> &data, const uint64_t DATA_SIZE, const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;
    std::string transformed_data(std::begin(data), std::begin(data) + DATA_SIZE);
    LOG_INFO << "bytes count: " << DATA_SIZE << "; data: " << transformed_data;
    start_read();
}

void ClientController::handle_write(const uint64_t DATA_SIZE, const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;
    LOG_DEBUG << "counts bytes was sent:" << DATA_SIZE;
    handle_error(error);
}

}   // !controllers;
}   // !client;
}   // !mc;
}   // !bukhtagram;