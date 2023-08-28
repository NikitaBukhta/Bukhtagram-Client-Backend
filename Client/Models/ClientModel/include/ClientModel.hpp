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

#ifndef BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_CLIENTMODEL_HPP
#define BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_CLIENTMODEL_HPP

#include "IClientModel.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <mutex>
#include <memory>

namespace bukhtagram {
namespace mc {
namespace client {
namespace models {

class ClientModel : public IClientModel {
public:
    ClientModel(std::weak_ptr<boost::asio::io_context> io_context);
    virtual ~ClientModel(void) = default;

    // Getters starts;

    std::weak_ptr<boost::asio::io_context> io_context(void) const override;
    std::weak_ptr<boost::asio::ip::tcp::socket> socket(void) const override;

    // Getters ends;

    // Setters starts;

    // Setters ends;

private:
    // Private Setters starts;

    bool set_io_context(std::weak_ptr<boost::asio::io_context> val);

    // Private Setters ends;

    // Private Update methods starts

    bool update_socket(void);

    // Private Update methods ends

private:
    mutable std::mutex m_io_context_mutex;
    std::shared_ptr<boost::asio::io_context> m_io_context;

    mutable std::mutex m_socket_mutex;
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};

}   // !models;
}   // !client;
}   // !mc;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_CLIENTMODEL_HPP;