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

#ifndef BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_ICLIENTMODEL_HPP
#define BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_ICLIENTMODEL_HPP

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <memory>

namespace bukhtagram {
namespace mc {
namespace client {
namespace models {

class IClientModel {
public:
    // Getters starts;

    virtual std::weak_ptr<boost::asio::io_context> io_context(void) const = 0;
    virtual std::weak_ptr<boost::asio::ip::tcp::socket> socket(void) const = 0;

    // Getters ends;

    // Setters starts;

    // Setters ends;
};

}   // !models;
}   // !client;
}   // !mc;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERCLIENT_CLIENT_MODELS_CLIENT_ICLIENTMODEL_HPP;