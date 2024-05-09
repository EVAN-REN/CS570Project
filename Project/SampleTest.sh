mkdir -p SampleResult

for i in {1..15}
do
  # 构造输入文件名和输出文件名
  input_file="SampleTestCases/intput${i}.txt"
  output_file="./Result/SampleOuroutput${i}_basic.txt"

  # 执行 basic.sh 脚本
  ./basic.sh $input_file $output_file
done

for i in {1..15}
do
  # 构造输入文件名和输出文件名
  input_file="SampleTestCases/intput${i}.txt"
  output_file="./Result/SampleOuroutput${i}_efficient.txt"

  # 执行 efficient.sh 脚本
  ./efficient.sh $input_file $output_file
done

