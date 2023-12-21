#define ARR_SIZE 10

int main(){
  int* array = new int[ARR_SIZE];
  for( int i=0; i<10; ++i ){
    array[i] = i * 10;
  }
  int* tmp_array = new int[2*ARR_SIZE];
  for( int i=0; i<10; ++i ){
    tmp_array[i] = array[i];
  }
  for( int i=11; i<20; ++i ){
    tmp_array[i] = i*10;
  }
  array = tmp_array;
  return 0;
}