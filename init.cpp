#include <unordered_map>
#include <functional>
#include <iostream>
#include <cstdint>
#include <string>

#ifndef NDEBUG
#define DEBUG(X) { std::cout << X << '\n'; }
#else
#define DEBUG(X)
#endif

std::unordered_map<std::string, std::function<void(int64_t&, int64_t)>> Operator = {
	{"+", [](int64_t& Operate, int64_t Value) {
		Operate += Value;
	}},

	{"-", [](int64_t& Operate, int64_t Value) {
		Operate -= Value;
	}},

	{"*", [](int64_t& Operate, int64_t Value) {
		Operate *= Value;
	}},

	{"/", [](int64_t& Operate, int64_t Value) {
		Operate /= Value;
	}}
};

int main() {
	while (true) {
        //Entrada.
		std::string Calculate;
		std::getline(std::cin, Calculate, '\n');

		//Registradores
		std::string Character;
		std::string Operat; 
		std::string Number; 
		int64_t Result = 0;

		bool Initiated = false;

        //Se talvez tiver erro, Isso aqui vai avisar.
		for (unsigned int I = 0; I < Calculate.length(); I++) {
			Character = Calculate[I];
			DEBUG("CHARACTER ATUAL: \"" << Character << '\"');
            //
			if (Character == " ") {
				DEBUG("ESPACO IGNORADO");
				continue;
			} else if (Operator.find(Character) != Operator.end()) {
				Operat = Character;
				DEBUG("OPERADOR PENDENTE GUARDADO");
			} else {
				Number += Character;
				DEBUG("NUMERO ADICIONADO");
				Character = Calculate[I + 1];

                //A calculadora em si, é isso aqui.
				if (Character[0] == '\0' || Character == " " || (Operator.find(Character) != Operator.end())) {
					if (!Initiated) {
						Result = std::stoll(Number);
						DEBUG("RESULTADO INICIAL: " << Number);
						Number = ""; Initiated = true;
						continue;
					} else if (!Operat.empty()) {
						DEBUG("OERADOR PENDENTE RESOLVIDO: " << Result << ' ' << Operat << ' ' << Number);
						Operator[Operat](Result, std::stoll(Number));
						Number = "";
						continue;
					}
				}
			}
		}
		std::cout << "Resultado: " << Result << '\n';
	}
}
