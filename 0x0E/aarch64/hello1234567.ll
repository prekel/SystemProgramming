@helloWorldString = constant [4 x i8] c"%d\0A\00"
@n = constant i32 1234

define i32 @main() {
  %1 = call i32 (i8*, i32, ...) @printf(i8*  getelementptr ([4 x i8], [4 x i8]* @helloWorldString, i32 0, i32 0), 
                                         i32 123123)
  ret i32 0
}

declare i32 @printf(i8*, i32, ...)

