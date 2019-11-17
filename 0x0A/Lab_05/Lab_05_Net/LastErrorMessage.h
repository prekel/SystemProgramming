#ifndef LASTERRORMESSAGE_H
#define LASTERRORMESSAGE_H

int LastError();

char* LastErrorMessage();

char* ErrorMessage(int error);

void PrintLastErrorMessage();

void PrintErrorMessage(int error);

#endif //LASTERRORMESSAGE_H
