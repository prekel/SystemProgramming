%struct.Matrix = type { i32, i32, i32** }

define i1 @IsOnly(%struct.Matrix* nocapture readonly, i32, i1 zeroext) {
  %4 = getelementptr inbounds %struct.Matrix, %struct.Matrix* %0, i64 0, i32 0
  %5 = load i32, i32* %4
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %7, label %34

7:                                                ; preds = %3
  %8 = getelementptr inbounds %struct.Matrix, %struct.Matrix* %0, i64 0, i32 1
  %9 = load i32, i32* %8
  %10 = icmp sgt i32 %9, 0
  %11 = getelementptr inbounds %struct.Matrix, %struct.Matrix* %0, i64 0, i32 2
  %12 = sext i32 %1 to i64
  %13 = sext i32 %9 to i64
  %14 = sext i32 %5 to i64
  br label %15

15:                                               ; preds = %7, %31
  %16 = phi i64 [ 0, %7 ], [ %32, %31 ]
  br i1 %10, label %17, label %31

17:                                               ; preds = %15
  %18 = load i32**, i32*** %11
  %19 = getelementptr inbounds i32*, i32** %18, i64 %12
  %20 = load i32*, i32** %19
  %21 = getelementptr inbounds i32, i32* %20, i64 %16
  %22 = load i32, i32* %21
  br label %25

23:                                               ; preds = %25
  %24 = icmp slt i64 %30, %13
  br i1 %24, label %25, label %31

25:                                               ; preds = %17, %23
  %26 = phi i64 [ 0, %17 ], [ %30, %23 ]
  %27 = getelementptr inbounds i32, i32* %20, i64 %26
  %28 = load i32, i32* %27
  %29 = icmp eq i32 %22, %28
  %30 = add nuw nsw i64 %26, 1
  br i1 %29, label %34, label %23

31:                                               ; preds = %23, %15
  %32 = add nuw nsw i64 %16, 1
  %33 = icmp slt i64 %32, %14
  br i1 %33, label %15, label %34

34:                                               ; preds = %31, %25, %3
  %35 = phi i1 [ true, %3 ], [ false, %25 ], [ true, %31 ]
  ret i1 %35
}

define i32 @main() {
  ret i32 0
}

