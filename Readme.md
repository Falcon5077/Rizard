본 디렉토리의 파일들은 21년6월8일(화) 진행되었던  
컴퓨터공학창의설계 수업에서 기말과제로써 제작된 파일들입니다.

---

## 본 파일에서는 다음의 파일들의 사용방법에 대해 설명하기 위해 쓰여졌습니다.

-Encoding.c  
-Decoding.c  
-adversary.out

---

**파일 내용 설명**

Encoding.c: test_sample1.txt 등의 약속된 형식이 갖춰진 txt파일을 압축하고 변조로 부터 복원하기 위해 규칙에 따라 bin파일로 변환하는 코드가 포함된 파일입니다.

◎adversary.out: Encoding.c로 변환 및 압축된 bin파일의 지정한 갯수만큼 무작위 위치의 문자아스키코드값을 무작위값으로 변환한다.

◎Decoding.c: adversary.out을 통해 변조된 파일에서 변조된 값들을 본래 Encoding.c 파일로 압축할 당시의 원본파일과 같이 복원함과 동시에 압축된 내용 또한 원본파일과 동일하게 압축해제한다.

---

**각 파일들의 사용방법**

- Encoding.c : gcc Encoding.c -o Encoding.out
- Decoding.c : gcc Decoding.c -o Decoding.out
- Encoding.out : ./Encoding.out FILENAME_FOR_ENCODING OUTPUT_FILENAME
- adversary.out : ./adversary FILENAME INT
- Decoding.out : ./Decoding.out FILENAME_FOR_DECODING OUTPUT_FILENAME

1. Encoding.out 으로 텍스트 파일을 인코딩한다.
2. adversary.out 으로 텍스트 파일을 변조한다.
3. Decoding,out 으로 변조된 파일을 디코딩한다.
