SIMPLE_COMPUTER = mySimpleComputer
CONSOLE = console
CONSOLE_PR01 = console/pr01

all: build

build:
	@echo "Сборка проекта..."
	@make -C $(SIMPLE_COMPUTER)
	@make -C $(CONSOLE)

run:
	@echo "Запуск программы..."
	@$(CONSOLE_PR01)

clean:
	@echo "Очистка проекта..."
	@rm -f $(SIMPLE_COMPUTER)/libmysimplecomputer.a $(CONSOLE)/pr01

