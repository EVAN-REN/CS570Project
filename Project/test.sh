mkdir -p Result

for i in {1..15}
do
  input_file="./datapoints/in${i}.txt"
  output_file="./Result/Ouroutput${i}_basic.txt"

  ./basic.sh $input_file $output_file
done

for i in {1..15}
do
  input_file="./datapoints/in${i}.txt"
  output_file="./Result/Ouroutput${i}_efficient.txt"

  ./efficient.sh $input_file $output_file
done

