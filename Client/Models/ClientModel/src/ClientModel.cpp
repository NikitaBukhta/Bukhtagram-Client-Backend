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

#include "ClientModel.hpp"

#include <iostream>

namespace bukhtagram {
namespace mc {
namespace client {
namespace models {

ClientModel::ClientModel(std::weak_ptr<boost::asio::io_context> io_context) {
    set_io_context(io_context);
    update_socket();
}

/*
 *  Getters starts;
 */

std::weak_ptr<boost::asio::io_context> ClientModel::io_context(void) const {
    std::lock_guard<std::mutex> guard(m_io_context_mutex);
    return m_io_context;
}

std::weak_ptr<boost::asio::ip::tcp::socket> ClientModel::socket(void) const {
    std::lock_guard<std::mutex> guard(m_socket_mutex);
    return m_socket;
}

/*
 *  Getters ends;
 */

/*
 *  Setters starts;
 */

/*
 *  Setters ends;
 */

/*
 *  Private Setters starts;
 */

bool ClientModel::set_io_context(std::weak_ptr<boost::asio::io_context> val) {
    std::lock_guard<std::mutex> guard(m_io_context_mutex);
    auto new_ptr = val.lock();
    if (new_ptr.get() && m_io_context.get() != new_ptr.get()) {
        m_io_context = new_ptr;
        return true;
    }
    return false;
}

/*
 *  Private Setters ends;
 */

/*
 *  Private Update methods starts;
 */

bool ClientModel::update_socket(void) {
    std::lock_guard<std::mutex> guard(m_io_context_mutex);
    if (m_io_context.get()) {
        std::lock_guard<std::mutex> guard(m_socket_mutex);
        m_socket = std::make_shared<boost::asio::ip::tcp::socket>(*m_io_context);
        return true;
    }
    return false;
}

/*
 *  Private Update methods ends;
 */

}   // !models;
}   // !client;
}   // !mc;
}   // !bukhtagram;