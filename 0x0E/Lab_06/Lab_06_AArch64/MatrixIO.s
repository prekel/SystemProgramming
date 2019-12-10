.text

	.global	ReadMN
ReadMN:
	mov x0, #4
	ret

	.global	ReadMatrix
ReadMatrix:
	mov x0, #5
	ret

	.global	WriteMatrix
WriteMatrix:
	mov x0, #6
	ret
