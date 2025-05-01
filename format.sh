# Find all .cpp files respecting .gitignore rules
git ls-files --cached --others --exclude-standard "*.cpp" | while read file; do
    sed -i 's/#pragma omp/\/\/#pragma omp/g' "$file"
    clang-format -i "$file"
    sed -i 's/\/\/ *#pragma omp/#pragma omp/g' "$file"
    echo "Processed: $file"
done