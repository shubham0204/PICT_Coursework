from enum import Enum

class ConditionCodes( Enum ):
    LT = 1
    LE = 2
    EQ = 3
    GT = 4
    GE = 5
    ANY = 6

class RegisterCodes( Enum ):
    AREG = 1
    BREG = 2
    CREG = 3
    DREG = 4
