#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

// Asegúrate de incluir nlohmann/json.hpp en tu proyecto o instala la biblioteca json.hpp de nlohmann

// Función para manejar la respuesta HTTP y almacenarla en una cadena
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

// Función para realizar una solicitud GET a Firebase
std::string httpGet(const std::string& url) {
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		// Realiza la solicitud GET
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Error en curl: " << curl_easy_strerror(res) << std::endl;
		}

		// Limpieza de curl
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}

int main() {
	// URL de tu Firebase Realtime Database con el nodo que deseas leer (incluye tu token de autenticación)
	std::string database_url = "https://hydrominer-d3d61-default-rtdb.firebaseio.com/usuarios.json?auth=TU_TOKEN";

	// Realiza la solicitud HTTP GET
	std::string respuesta = httpGet(database_url);

	// Muestra la respuesta JSON obtenida
	std::cout << "Datos obtenidos de Firebase: " << respuesta << std::endl;

	return 0;
}
