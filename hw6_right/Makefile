# Если изменили имя теста, то надо изменить его и здесь тоже
TEST_EXEC = tests/test.py

make: setup.py
	sudo ./setup.py install
	chmod +x $(TEST_EXEC)
	./$(TEST_EXEC)
