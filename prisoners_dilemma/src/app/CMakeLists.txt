cmake_minimum_required(VERSION 3.27)

add_executable(prisoners_dilemma)

target_sources(prisoners_dilemma PRIVATE main.cpp prisoners_dilemma.cpp)
target_link_libraries(prisoners_dilemma PRIVATE 
    core 
    utils 
    strategy_api 
    all_cooperate 
    all-defect
    combined 
    go-by-majority 
    random 
    soft-tit-for-tat 
    tough-tit-for-tat
)
target_include_directories(prisoners_dilemma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
