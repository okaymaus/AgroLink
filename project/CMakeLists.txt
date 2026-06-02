cmake_minimum_required(VERSION 3.12)
project(AgroLink LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/models/User.cpp
    src/models/Customer.cpp
    src/models/Producer.cpp
    src/models/Admin.cpp
    src/models/Product.cpp
    src/models/Fruit.cpp
    src/models/Vegetable.cpp
    src/models/DairyProduct.cpp
    src/models/HandmadeProduct.cpp
    src/models/Order.cpp
    src/models/Review.cpp
    src/models/Village.cpp
    src/services/UserService.cpp
    src/services/ProductService.cpp
    src/services/OrderService.cpp
    src/services/ReviewService.cpp
    src/marketplace/Marketplace.cpp
    src/menu/ConsoleMenu.cpp
    src/main.cpp
)

# Header files (for IDE visibility)
set(HEADERS
    include/models/User.h
    include/models/Customer.h
    include/models/Producer.h
    include/models/Admin.h
    include/models/Product.h
    include/models/Fruit.h
    include/models/Vegetable.h
    include/models/DairyProduct.h
    include/models/HandmadeProduct.h
    include/models/Order.h
    include/models/Review.h
    include/models/Village.h
    include/repositories/Repository.h
    include/services/UserService.h
    include/services/ProductService.h
    include/services/OrderService.h
    include/services/ReviewService.h
    include/marketplace/Marketplace.h
    include/menu/ConsoleMenu.h
)

add_executable(AgroLink ${SOURCES} ${HEADERS})
