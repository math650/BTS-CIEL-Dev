#include <pigpio.h>
#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include "TVI.h"

#define DHT22_GPIO 4

bool temp_dht(float *temperature)
{
    uint8_t data[5] = {0};

    // Signal de démarrage
    gpioSetMode(DHT22_GPIO, PI_OUTPUT);
    gpioWrite(DHT22_GPIO, 0);
    usleep(2000);  // Au moins 1 ms pour le DHT22

    // Relâche la ligne DATA
    gpioSetMode(DHT22_GPIO, PI_INPUT);
    gpioSetPullUpDown(DHT22_GPIO, PI_PUD_UP);

    uint32_t debut = gpioTick();

    // Réponse initiale du capteur
    while (gpioRead(DHT22_GPIO) == PI_HIGH) {
        if (gpioTick() - debut > 200)
            return false;
    }

    debut = gpioTick();
    while (gpioRead(DHT22_GPIO) == PI_LOW) {
        if (gpioTick() - debut > 200)
            return false;
    }

    debut = gpioTick();
    while (gpioRead(DHT22_GPIO) == PI_HIGH) {
        if (gpioTick() - debut > 200)
            return false;
    }

    // Lecture des 40 bits
    for (int bit = 0; bit < 40; ++bit) {
        debut = gpioTick();

        while (gpioRead(DHT22_GPIO) == PI_LOW) {
            if (gpioTick() - debut > 100)
                return false;
        }

        uint32_t debutEtatHaut = gpioTick();

        while (gpioRead(DHT22_GPIO) == PI_HIGH) {
            if (gpioTick() - debutEtatHaut > 150)
                return false;
        }

        uint32_t dureeEtatHaut = gpioTick() - debutEtatHaut;

        if (dureeEtatHaut > 50)
            data[bit / 8] |= static_cast<uint8_t>(1 << (7 - bit % 8));
    }

    // Vérifie le checksum
    uint8_t checksum =
        static_cast<uint8_t>(data[0] + data[1] + data[2] + data[3]);

    if (checksum != data[4])
        return false;

    // Décode la température : bit 15 = signe, les autres bits = dixièmes de degré
    int16_t valeurBrute =
        static_cast<int16_t>((data[2] << 8) | data[3]);

    bool negatif = (valeurBrute & 0x8000) != 0;
    valeurBrute &= 0x7FFF;

    *temperature = valeurBrute / 10.0f;
    if (negatif)
        *temperature = -*temperature;

    return true;
}

int main()
{
    TVI afficheur;

    if (gpioInitialise() < 0) {
        std::printf("Erreur : impossible d'initialiser pigpio.\n");
        return 1;
    }

    float temperature;

    if (!temp_dht(&temperature)) {
        std::printf("Erreur de lecture du DHT22.\n");
        gpioTerminate();
        return 1;
    }

    char temperatureTexte[16];
std::snprintf(temperatureTexte, sizeof(temperatureTexte), "%.1f", temperature);

std::string message =
    "D'hordhain, Andres, Martin - " + std::string(temperatureTexte) + " C";

    std::printf("%s\n", message.c_str());
    afficheur.afficher_message_tvi(message);

    gpioTerminate();
    return 0;
}
