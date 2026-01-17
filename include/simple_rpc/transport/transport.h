#pragma once
#include <string>

namespace s_rpc {

namespace transport {

class Transport {
public:
    virtual ~Transport() = default;
    virtual bool send_data(const std::string& data) = 0;
    virtual std::string receive_data() = 0;
};

} // namespace transport

} // namespace s_rpc