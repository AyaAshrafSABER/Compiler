//
// Created by AYAOSMAN on 3/25/2019.
//

#ifndef COMPILER_ERRORHANDLER_H
#define COMPILER_ERRORHANDLER_H

#include <string>

class ErrorHandler {
public:

    enum Error {
        lexicalError,

    };
    static const std::string errors[];
};



#endif //COMPILER_ERRORHANDLER_H
