# betterToyotaAngleSensorForOP
**NEW SHIZ**

Magnetic position sensor with magnet:

https://www.digikey.com/product-detail/en/ams/AS5048B-TS_EK_AB/AS5048B-AB-1.0-ND/3188613

Datasheet:

https://www.mouser.com/ds/2/588/AS5048_DS000298_3-00-522570.pdf

Arduino:

https://www.amazon.com/gp/product/B0713XK923/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

CAN Boards:

https://www.amazon.com/HiLetgo-MCP2515-TJA1050-Receiver-Arduino/dp/B01D0WSEWU/ref=sxbs_sxwds-stvp?keywords=MCP2515&pd_rd_i=B01D0WSEWU&pd_rd_r=55913e25-7bfa-42ba-b733-50fc491a1e5a&pd_rd_w=9tyYm&pd_rd_wg=gJSDp&pf_rd_p=a6d018ad-f20b-46c9-8920-433972c7d9b7&pf_rd_r=WJENW45G8ZVXYJ0ZCYPR&qid=1559583482&s=hi











**OLD SHIZ**
Parts:
AST-CAN485 https://learn.sparkfun.com/tutorials/ast-can485-hookup-guide?_ga=2.86221464.1061059386.1557240527-391850435.1557240527

Rotary Encoder - 1024 P/R (Quadrature) https://www.sparkfun.com/products/11102

Single LS7366R Quadrature Encoder Buffer https://www.superdroidrobots.com/shop/item.aspx/single-ls7366r-quadrature-encoder-buffer/2397/

USB to TTL Adapter https://www.amazon.com/gp/product/B075N82CDL/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1

MCIGICM IC 7805 Voltage Regulator, L7805 https://www.amazon.com/gp/product/B07BDFMQF6/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1

You could cheap out and get inexpensive parts, but I wanted the best to rule out hardware issues and have a long term solution. The CAN dev board is 16Mhz for example, so lag shouldn't be a concern.

Arne has some additional hacks to enable the steering wheel buttons to do stuff on his Toyota Rav 4, should be the same for Prius:
https://github.com/arne182/DSUButtons

I could approach this a few different ways. First, I could intercept the stock steering sensor and output my own sensor - such as:
https://github.com/Phrewfuf/sas-scaler

Instead, what I'm doing is using the OEM steering sensor to set the encoder POS to the initial position of the OEM steering angle sensor.

I likely need to come up with some sort of calibration method, ie move the wheel x degrees and count the encoder steps to scale the values accordingly.

NOTES, SPAM
See how Honda reports the actual angle in one message, than the garbage 1/15th fraction, angle shit Toyota does and use that.
Set the generated CAN messages to have a high enough priority, but not too high (maybe +1 the stock steering sensor if no collision)
