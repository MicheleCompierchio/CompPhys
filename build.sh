#!/bin/bash

# --- Colors ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# --- Compilation Function ---
compile_file() {
    local FILE_PATH="$1"
    
    if [ ! -f "$FILE_PATH" ]; then
        echo -e "${RED}Error: File '$FILE_PATH' does not exist.${NC}"
        exit 1
    fi

    local DIR=$(dirname "$FILE_PATH")
    local FILENAME=$(basename "$FILE_PATH" .cpp)

    mkdir -p "$DIR/bin"
    local OUTPUT_PATH="$DIR/bin/$FILENAME"

    echo -e "\n${CYAN}Compiling ${YELLOW}$FILE_PATH${CYAN}...${NC}"
    g++ -std=c++17 -Wall "$FILE_PATH" -o "$OUTPUT_PATH"

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✅ Build completed successfully!${NC}\n"
        echo -e "You can run the program with the following command:"
        echo -e "  ${YELLOW}$OUTPUT_PATH${NC}\n"
    else
        echo -e "${RED}❌ Error during compilation.${NC}"
        exit 1
    fi
}

# If a file was passed as an argument, use non-interactive mode
if [ -n "$1" ]; then
    compile_file "$1"
    exit 0
fi

# --- Interactive Mode ---
clear
echo -e "${CYAN}"
cat << "EOF"
   ___                     ____  _               
  / __|___ _ __  _ __ ___ |  _ \| |__  _   _ ___ 
 | |  / _ \ '_ \| '_ ` _ \| |_) | '_ \| | | / __|
 | |__| (_) | | | | | | | | |  __/| | | | |_| \__ \
  \____\___/|_| |_|_| |_| |_|_|   |_| |_|\__, |___/
                                         |___/     
             Interactive Build System                 
EOF
echo -e "${NC}"

# 1. Find directories containing .cpp files
DIRS=()
while IFS= read -r line; do
    DIRS+=("$line")
done < <(find . -name "*.cpp" -not -path "*/\.*" -not -path "*/bin*" -exec dirname {} \; | sed 's|^\./||' | sort | uniq)

if [ ${#DIRS[@]} -eq 0 ]; then
    echo -e "${RED}No projects found with .cpp files.${NC}"
    exit 1
fi

echo -e "${YELLOW}[1] Select project folder:${NC}"
for i in "${!DIRS[@]}"; do
    echo "  $((i+1))) ${DIRS[$i]}"
done
echo ""
read -p "Enter number (1-${#DIRS[@]}): " dir_idx

if ! [[ "$dir_idx" =~ ^[0-9]+$ ]] || [ "$dir_idx" -lt 1 ] || [ "$dir_idx" -gt "${#DIRS[@]}" ]; then
    echo -e "${RED}Invalid choice. Exiting.${NC}"
    exit 1
fi
SELECTED_DIR="${DIRS[$((dir_idx-1))]}"

# 2. Find .cpp files in the selected directory
echo ""
echo -e "${YELLOW}[2] Select file to compile in '$SELECTED_DIR':${NC}"

FILES=()
while IFS= read -r line; do
    FILES+=("$line")
done < <(find "$SELECTED_DIR" -maxdepth 1 -name "*.cpp" | sed "s|^$SELECTED_DIR/||" | sort)

if [ ${#FILES[@]} -eq 0 ]; then
    echo -e "${RED}No .cpp files found in $SELECTED_DIR.${NC}"
    exit 1
fi

for i in "${!FILES[@]}"; do
    echo "  $((i+1))) ${FILES[$i]}"
done
echo ""
read -p "Enter number (1-${#FILES[@]}): " file_idx

if ! [[ "$file_idx" =~ ^[0-9]+$ ]] || [ "$file_idx" -lt 1 ] || [ "$file_idx" -gt "${#FILES[@]}" ]; then
    echo -e "${RED}Invalid choice. Exiting.${NC}"
    exit 1
fi
SELECTED_FILE="${FILES[$((file_idx-1))]}"

# 3. Compile the selected file
compile_file "$SELECTED_DIR/$SELECTED_FILE"
