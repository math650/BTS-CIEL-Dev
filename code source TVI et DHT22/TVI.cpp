#include "TVI.h"

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

void TVI::configurer_port_serie(int fd)
{
    struct termios options;

    if (tcgetattr(fd, &options) != 0) {
        perror("Erreur tcgetattr");
        return;
    }

    // Vitesse : 1200 bauds
    cfsetispeed(&options, B1200);
    cfsetospeed(&options, B1200);

    // Active la réception et ignore le contrôle du modem
    options.c_cflag |= (CLOCAL | CREAD);

    // 7 bits, parité paire, 1 bit de stop
    options.c_cflag |= PARENB;
    options.c_cflag &= ~PARODD;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS7;

    // Mode non canonique
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Pas de traitement de sortie
    options.c_oflag &= ~OPOST;

    // Pas de contrôle logiciel
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Lecture non bloquante minimale
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("Erreur tcsetattr");
    }
}

void TVI::tvi_on()
{
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0) {
        perror("Erreur ouverture /dev/ttyUSB0");
        return;
    }

    configurer_port_serie(fd);

    const unsigned char trame[] = {
        0x02,       // STX
        0x54,       // T
        0x31,       // 1
        0x30,       // 0
        0x41,       // A : allumage
        0x0D,       // CR
        0x03        // ETX
    };

    ssize_t resultat = write(fd, trame, sizeof(trame));

    if (resultat < 0) {
        perror("Erreur envoi commande TVI ON");
    }

    tcdrain(fd);
    close(fd);
}

void TVI::tvi_off()
{
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0) {
        perror("Erreur ouverture /dev/ttyUSB0");
        return;
    }

    configurer_port_serie(fd);

    const unsigned char trame[] = {
        0x02,       // STX
        0x54,       // T
        0x31,       // 1
        0x30,       // 0
        0x42,       // B : extinction
        0x0D,       // CR
        0x03        // ETX
    };

    ssize_t resultat = write(fd, trame, sizeof(trame));

    if (resultat < 0) {
        perror("Erreur envoi commande TVI OFF");
    }

    tcdrain(fd);
    close(fd);

    std::printf("TVI OFF\n");
}

void TVI::afficher_message_tvi(const std::string& message)
{
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0) {
        perror("Erreur ouverture /dev/ttyUSB0");
        return;
    }

    configurer_port_serie(fd);

    /*
     * Trame :
     * STX T 1 0 O 0 1 message CR ETX
     */
    std::string trame;

    trame += static_cast<char>(0x02);  // STX
    trame += "T10O01";
    trame += message;
    trame += static_cast<char>(0x0D);  // CR
    trame += static_cast<char>(0x03);  // ETX

    ssize_t resultat = write(fd, trame.c_str(), trame.size());

    if (resultat < 0) {
        perror("Erreur envoi message TVI");
    }

    tcdrain(fd);
    close(fd);
}



