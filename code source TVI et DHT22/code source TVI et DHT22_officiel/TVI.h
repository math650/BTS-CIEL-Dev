#ifndef TVI_H
#define TVI_H

#include <string>

class TVI
{
public:
    void configurer_port_serie(int fd);
    void tvi_on();
    void tvi_off();
    void afficher_message_tvi(const std::string& message);
};

#endif
