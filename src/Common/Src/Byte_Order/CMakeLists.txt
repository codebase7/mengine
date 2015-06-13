# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Define includes.
set (BYTE_ORDER_INCLUDES Byte_Order.c
Byte_Order_Floating_Points.c
Byte_Order_Integers.c)

# Define static library.
add_library (Common_Byte_Order_Multiverse_Engine_Static STATIC ${BYTE_ORDER_INCLUDES})

# Define shared library.
add_library (Common_Byte_Order_Multiverse_Engine SHARED ${BYTE_ORDER_INCLUDES})
