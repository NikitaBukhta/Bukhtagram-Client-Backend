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

#ifndef BUKHTAGRAM_MESSENGERCLIENT_CLIENT_VIEWS_CLIENTVIEW_HPP
#define BUKHTAGRAM_MESSENGERCLIENT_CLIENT_VIEWS_CLIENTVIEW_HPP

#include "ClientModel.hpp"
#include "ClientController.hpp"

#include <boost/asio/io_context.hpp>

#include <memory>
#include <string>
#include <inttypes.h>

namespace bukhtagram {
namespace mc {
namespace client {
namespace views {

class ClientView {
public:
    ClientView(std::weak_ptr<boost::asio::io_context> io_context_weak);
    virtual ~ClientView(void) = default;

    bool run(const std::string &address, uint16_t port);
    void start_reading_signals(void);

protected:
    // TODO: constructor for UT, where args should be model and controller;

private:
    void send_message(const std::string &message);

private:
    std::shared_ptr<models::IClientModel> m_client_model;
    std::shared_ptr<controllers::IClientController> m_client_controller;
};

}   // !views;
}   // !client;
}   // !mc;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERCLIENT_CLIENT_VIEWS_CLIENTVIEW_HPP;