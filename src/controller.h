#include <string>

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

enum COMMAND {
    ADD, DEL, QUERY, WQUERY
};

class Controller {
 private:
    virtual COMMAND getCommand(std::string* command);

 public:
    static const std::string ADD_CMD;

    static const std::string DEL_CMD;

    static const std::string QUERY_CMD;

    static const std::string WQUERY_CMD;

    virtual void call(std::string* command);
};

#endif  // SRC_CONTROLLER_H_
