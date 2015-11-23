#include <string>

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

class Controller {
 public:
    virtual void call(std::string* command);
};

#endif  // SRC_CONTROLLER_H_
