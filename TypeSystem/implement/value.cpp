// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../value.h"

namespace Oblivia{
    Type Value::getType()const{
        return this->type;
    }

    std::ostream&operator<<(std::ostream&os,const Type&a){
        switch(a){
            case Type::Null:os<<"Null";break;
            case Type::Number:os<<"Number";break;
            case Type::Array:os<<"Array";break;
            case Type::Function:os<<"Function";break;
            case Type::Object:os<<"Object";break;
            case Type::String:os<<"String";break;
            case Type::Reference:os<<"Reference";break;
        }
        return os;
    }

    std::ostream&operator<<(std::ostream&os,const Value&a){
        a.print(os);
        return os;
    }
}
