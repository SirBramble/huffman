# IP024 Huffman IC logo gen
## To run
1. Copy text to be encoded into `huffman_gen/vanilla.txt`
2. Run `logo_huffman/compile.sh`
3. Include `logo_huffman/lib/include/huffman_logo.h` in your project
4. Call `print_logo_hoffman(uart_handle, &ip024_uart_putc)` to print the logo to IP024 UART