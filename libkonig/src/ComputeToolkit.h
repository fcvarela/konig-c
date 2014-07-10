#ifndef KONIG_COMPUTE_TOOKIT_H
#define KONIG_COMPUTE_TOOKIT_H

#include <map>

class ComputeToolkit {
public:
    static std::map<uint8_t, std::string> get_devices();

};

#endif
