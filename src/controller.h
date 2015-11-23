#include <string>
#include <vector>

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

enum COMMAND {
    ADD, DEL, QUERY, WQUERY
};

class Controller {
 private:
    virtual COMMAND getCommand(std::string* command);

    virtual void add(std::string* command);

    virtual void del(std::string* command);

    virtual std::vector<std::string>* query(std::string* command);

    virtual std::vector<std::string>* wquery(std::string* command);

 public:
    static const std::string ADD_CMD;

    static const std::string DEL_CMD;

    static const std::string QUERY_CMD;

    static const std::string WQUERY_CMD;

    virtual void call(std::string* command);
};

#endif  // SRC_CONTROLLER_H_
