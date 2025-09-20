add_library(controllers SHARED  ./PersonCreateController.cpp ./PersonDeleteByIdController.cpp ./PersonGetAllController.cpp ./PersonGetByIdController.cpp ./PersonUpdateByIdController.cpp ./DefaultController.cpp)
target_link_libraries(controllers repositories)
target_link_libraries(controllers util)
