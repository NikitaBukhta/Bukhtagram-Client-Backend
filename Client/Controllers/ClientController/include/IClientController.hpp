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

#ifndef BUKHTAGRAM_MESSENGERCLIENT_CLIENT_CONTROLLERS_ICLIENTCONTROLLER_HPP
#define BUKHTAGRAM_MESSENGERCLIENT_CLIENT_CONTROLLERS_ICLIENTCONTROLLER_HPP

#include <memory>
#include <string>

namespace bukhtagram {
namespace mc {
namespace client {
namespace controllers {

class IClientController {
public:
    virtual void run(void) = 0;
    virtual bool connect_to(const std::string &address, uint16_t port) = 0;
    virtual void send_message(const std::string &message) = 0;
};

}   // !controllers;
}   // !client;
}   // !mc;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERCLIENT_CLIENT_CONTROLLERS_ICLIENTCONTROLLER_HPP;