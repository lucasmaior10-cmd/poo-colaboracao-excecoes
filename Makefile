CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -Iinclude

.PHONY: test run
test:
	@test "$(ETAPA)" = "A" || (echo "Use make test ETAPA=A"; exit 2)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) tests/contrato.cpp -o build/contrato
	@./build/contrato
	@python3 tests/contrato.py

run:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp -o build/estacao
	@./build/estacao
	@python3 src/main.py
