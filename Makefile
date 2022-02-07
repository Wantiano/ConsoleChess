help:
	@echo Giving an argument is a must.

chess: main.cpp View/chessview.cpp Model/chessmodel.cpp Model/Pieces/pieces.cpp
	@clear
	@echo Compiling...
	@echo ________________________________________________________________________________________________
	@echo
	@g++ main.cpp View/ChessView.cpp Model/ChessModel.cpp Model/Pieces/pieces.cpp -Wall -O3 -o consolechess.out

tests: Model/Pieces/test.cpp Model/Pieces/pieces.cpp
	@clear
	@echo Compiling and running tests of Pieces...
	@echo ________________________________________________________________________________________________
	@echo
	@g++ Model/Pieces/test.cpp Model/Pieces/pieces.cpp -o tests.out
	@./tests.out
	@rm tests.out
	