include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Source files are explicitly listed to avoid building problems and unnecessary linking
set(RV_SRC src/RandomVariable.cpp
			src/Parametric.cpp
			src/NonParametric.cpp
			src/Normal.cpp
			src/Lognormal.cpp
			src/Weighted.cpp
			src/Unweighted.cpp
			src/RandomVariableContainer.cpp
			src/Translation.cpp
)

# include_directory function is ineffetive in Xcode
set(RV_INC 	inc/RandomVariable.h
			inc/Parametric.h
			inc/NonParametric.h
			inc/Normal.h
			inc/Lognormal.h
			inc/Weighted.h
			inc/Unweighted.h
			inc/RandomVariableContainer.h
			inc/Translation.h
)

add_library(RV ${RV_INC} ${RV_SRC})
