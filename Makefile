SIMPLE_COMPUTER = mySimpleComputer
TERM = myTerm
CONSOLE = console
CONSOLE_PR03 = console/console.a

all: build

build:
	@echo "Сборка проекта..."
	@make -C $(SIMPLE_COMPUTER)
	@make -C $(TERM)
	@make -C $(CONSOLE)

run:
	@echo "Запуск программы..."
	@$(CONSOLE_PR03)

clean:
	@echo "Очистка проекта..."
	@rm -f $(SIMPLE_COMPUTER)/libmysimplecomputer.a $(CONSOLE)/console.a $(TERM)/libmyterm.a

