help:
	@echo Giving an argument is a must.
	@echo "(Arguments: chess, piecetests, modeltests)"

chess: src/main.cpp src/View/chessview.cpp src/Model/chessmodel.cpp src/Model/Pieces/pieces.cpp
	@clear
	@echo Compiling...
	@echo _________________________________________
	@echo
	@g++ src/main.cpp src/View/chessview.cpp src/Model/chessmodel.cpp src/Model/Pieces/pieces.cpp -Wall -O3 -o consolechess.out

piecetests: src/Model/Pieces/piecetest.cpp src/Model/Pieces/pieces.cpp
	@clear
	@echo Compiling and running tests of Pieces...
	@echo _________________________________________
	@echo
	@g++ src/Model/Pieces/piecetest.cpp src/Model/Pieces/pieces.cpp -o piecetests.out
	@./piecetests.out
	@rm piecetests.out
	
modeltests: src/Model/modeltest.cpp src/View/chessview.cpp src/Model/chessmodel.cpp src/Model/Pieces/pieces.cpp
	@clear
	@echo Compiling and running tests of src/Model...
	@echo _________________________________________
	@echo
	@g++ src/Model/modeltest.cpp src/View/chessview.cpp src/Model/chessmodel.cpp src/Model/Pieces/pieces.cpp -o modeltests.out
	@./modeltests.out
	@rm modeltests.out