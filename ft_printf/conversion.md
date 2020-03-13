# CONVERSIONS

## %c

- [ ] flag와 width의 순서 지켜야함

### flag '-0# +'

- [ ] flag '-'만 사용가능 '0# +'는 에러처리 해야함
- [ ] flag '-'를 사용하는경우 width가 함께 사용되어야 제대로 작동함 / 그냥 '-'만 사용하면 의미 없음

### width '\*' 숫자

- [ ] 폭으로 입력되는 숫자의 개수만큼 공백을 출력함 (-가 있는경우 값 뒤로 -가 없는경우 값 앞으로)
- [ ] 폭으로 0이 입력될 수 없음 0은 flag로 인식
- [ ] width로 '\*'이 입력되는경우 인자로 width를 받아옴
- [ ] 입력된 숫자가 char보다 긴경우만 공백이 출력됨 / width가 1보다 큰경우만 작동함
- [ ] 출력될 길이보다 작거나 같은경우 무시됨

### precision '\*' 숫자

- [ ] 정확도가 입력되는경우 에러처리함

### length 'l' 'll' 'h' 'hh'

- [ ] %c %lc 만 사용가능 %hc %hhc %llc 에러 처리
- [ ] %c = int
- [ ] %lc = wint_t

## %s

### flag '-0# +'

- [ ] flag '-'만 사용가능 '0# +'는 에러처리 해야함
- [ ] flag '-'를 사용하는경우 width가 함께 사용되어야 제대로 작동함 / 그냥 '-'만 사용하면 의미 없음

### width '\*' '숫자'

- [ ] width로 0이 입력되지 않음 / flag로 인식함
- [ ] 총 길이보다 긴경우 공백이 출력됨 문자열이 10개면 11부터 공백이 하나씩 출력됨
- [ ] '-'flag가 없으면 앞에서 공백 출력됨 '-'flag가 있으면 뒤에서 공백 출력됨
- [ ] 길이가 작거나 같은경우 무시됨

#### %c와 %s의 경우 width가 길이보다 작거나 같은경우 무시 큰경우 문자열의 할당을 width로 할당 / 값을 제외한 나머지는 공백으로 입력

### precision '\*' '숫자'

- [ ] precision으로 입력된 숫자만큼 문자열이 출력됨
- [ ] \*이 precision으로 입력되면 매개변수로 받은 값이 출력됨
- [ ] precision으로 입력된 값이 문자열보다 긴경우 문자열 이상으로 출력되지 않음
- [ ] precision으로 0이 입력된경우 아무것도 출력되지 않음

### length 'l' 'll' 'h' 'hh'

- [ ] %s %ls 만 가능함
- [ ] %s = char \*
- [ ] %ls = wchar_t \*

## %p

### flag '-0# +'

- [ ] '-'만 가능함 그 외는 에러처리

### width '\*' '숫자'

- [ ] %s %c와 같이 작동함

### precision '\*' '숫자'

- [ ] 정확도가 입력되면 에러처리함

### length 'l' 'll' 'h' 'hh'

- [ ] %p = void \* / 그 이외에는 에러처리

## %d

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

- [ ] %d = int
- [ ] %hd = int
- [ ] %ld = long int

## %i

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

<!--  -->

## %u

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %x

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %X

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %%

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %n

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %f

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %g

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

## %e

### flag '-0# +'

### width '\*' '숫자'

### precision '\*' '숫자'

### length 'l' 'll' 'h' 'hh'

# print

- [ ] 값이 0보다 크거나 같은경우 값 % 256을 수행하여 값이 0~128 || 255인경우 stdout과 같은 값을 출력하고, 129~254까지의 값에서는 '?'를 출력함
- [ ] 값이 0보다 작은경우 (값 % 256) + 256 을 수행해서 양수와 같이 처리함
