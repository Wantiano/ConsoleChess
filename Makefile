help:
	@echo Giving an argument is a must.
	@echo (Arguments: chess, piecetests, modeltests)

chess: main.cpp View/chessview.cpp Model/chessmodel.cpp Model/Pieces/pieces.cpp
	@clear
	@echo Compiling...
	@echo _________________________________________
	@echo
	@g++ main.cpp View/chessview.cpp Model/chessmodel.cpp Model/Pieces/pieces.cpp -Wall -O3 -o consolechess.out

piecetests: Model/Pieces/piecetest.cpp Model/Pieces/pieces.cpp
	@clear
	@echo Compiling and running tests of Pieces...
	@echo _________________________________________
	@echo
	@g++ Model/Pieces/piecetest.cpp Model/Pieces/pieces.cpp -o piecetests.out
	@./piecetests.out
	@rm piecetests.out
	
modeltests: Model/modeltest.cpp View/chessview.cpp Model/chessmodel.cpp Model/Pieces/pieces.cpp
	@clear
	@echo Compiling and running tests of Model...
	@echo _________________________________________
	@echo
	@g++ Model/modeltest.cpp View/chessview.cpp Model/chessmodel.cpp Model/Pieces/pieces.cpp -o modeltests.out
	@./modeltests.out
	@rm modeltests.out