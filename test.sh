#! /bin/bash

mkdir -p -- test_results

for number in {01..25}
do
  ./subc -ast ./tiny_test_progs/tiny_$number > test_results/tree.$number
  status=$?

  if [ $status -ne 0 ]; then
    echo "Tiny Program #$number failed to generate an AST. ❌"
    break;
  fi

  OUTPUT=$(diff ./test_results/tree.$number ./tiny_test_progs/tiny_$number.tree)
  if [[ $OUTPUT ]]; then
      echo "Tiny Program #$number did not match the reference AST. ❌"
      echo "$OUTPUT"
      break;
  else
      echo "Tiny Program #$number matched the reference AST! ✅"
  fi
done

exit 0