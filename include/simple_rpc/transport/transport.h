#pragma once
#include <string>

namespace s_rpc {

class transport {
    virtual ~transport() = default;
    virtual bool send_data(const std::string& data) = 0;
    virtual std::string receive_data() = 0;
};

} //namespace s_rpc