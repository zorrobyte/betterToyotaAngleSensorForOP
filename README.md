# betterToyotaAngleSensorForOP

WIP BOM to supplement repo https://docs.google.com/spreadsheets/d/1Pn6zGi96R18uo3hBh6kgpqTcffqMBHuL74cx0rIaKcA/edit?usp=sharing

AS5047P eval board (comes with magnet):

https://www.digikey.com/product-detail/en/ams/AS5047P-TS_EK_AB/AS5047P-TS_EK_AB-ND/5452344

Arduino Library (default is 4096 PPR, possibly not needed):

http://www.massmind.org/techref/io/sensor/pos/enc/ENC2-47P-Arduino.htm

Datasheet:

https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf

Arduino:

https://www.amazon.com/gp/product/B0713XK923/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

CAN Boards:

https://www.amazon.com/HiLetgo-MCP2515-TJA1050-Receiver-Arduino/dp/B01D0WSEWU/ref=sxbs_sxwds-stvp?keywords=MCP2515&pd_rd_i=B01D0WSEWU&pd_rd_r=55913e25-7bfa-42ba-b733-50fc491a1e5a&pd_rd_w=9tyYm&pd_rd_wg=gJSDp&pf_rd_p=a6d018ad-f20b-46c9-8920-433972c7d9b7&pf_rd_r=WJENW45G8ZVXYJ0ZCYPR&qid=1559583482&s=hi

Library for CAN Boards:
https://github.com/autowp/arduino-mcp2515

Single LS7366R Quadrature Encoder Buffer
https://www.superdroidrobots.com/shop/item.aspx/single-ls7366r-quadrature-encoder-buffer/2397/

Library for Encoder buffer
https://github.com/SuperDroidRobots/Encoder-Buffer-Library

Some flat capped M3s (stainless works, try to stay away from highly ferrous materials)
https://www.amazon.com/iExcell-Stainless-Internal-Drives-Screws/dp/B07D686M7N/ref=sr_1_4?keywords=flat+cap+m3&qid=1560569375&s=gateway&sr=8-4

Basic instructions:
Connect both the CAN board and the LS7366R to the Arduino. Connect the AS5047P to the LS7366R.

Print these files:
https://a360.co/2X2c5dA

Extend the hole in the EPS motor shaft, tap it to M3, align the magnet holder, attach the AS5047P to the cap, snap it in, later superglue (small amount) the cap in after everything is working.

And then refingerprint your car, add the signals to cabana, offset the angle in OP, then BOOM! You are done.

OP Fork:
https://github.com/zorrobyte/openpilot/tree/devel_zorroangle
