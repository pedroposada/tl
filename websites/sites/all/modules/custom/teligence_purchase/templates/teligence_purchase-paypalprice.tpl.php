<!-- test url cart/paypal/price-confirmation -->

<div style="font-size: 16px; font-weight: bold; margin: 20px 20px 20px 0pt; font-family: Helvetica;">Join Livelinks: Confirm Order Details</div>
<div style="font-size: 13px; margin: 0pt; font-family: Helvetica;">
<table width="558px" cellspacing="0" cellpadding="0" border="0" style="background: none repeat scroll 0% 0% rgb(245, 245, 245);">
    <tbody style="border: medium none;">
        <tr>
            <td style="background: none repeat scroll 0% 0% rgb(0, 0, 0); padding: 10px; color: rgb(255, 255, 255); font-size: 14px; font-weight: bold;" colspan="2">Confirm Order</td>
        </tr>
        <?php if($hasEmail){ ?>
        <tr>
            <td style="padding: 20px 0pt 0pt 20px;">E-mail:</td>
            <td style="padding: 20px 0pt 0pt 20px;"><strong>Email</strong></td>
        </tr>
        <?php } ?>
        <tr>
            <td valign="top" style="padding: 20px 0pt 0pt 20px;">Order Details:</td>
            <td style="padding: 20px 0pt 0pt 20px;">
            <table width="90%" cellspacing="0" cellpadding="0" border="0">
                <tbody style="border: medium none;">
                    <tr>
                        <td align="left" style="padding: 0pt;">Package:</td>
                        <td style="padding: 0pt;"><strong>PackageMinutes minutes</strong></td>
                    </tr>
                    <tr>
                        <td align="left" style="padding: 20px 0pt 0pt;">Cost:</td>
                        <td style="padding: 20px 0pt 0pt;"><strong>$PackageAmountDollars</strong></td>
                    </tr>
                    <tr>
                        <td align="left" style="padding: 20px 0pt 10px;">Tax:</td>
                        <td style="padding: 20px 0pt 10px;"><strong>$TaxesAmountDollars</strong></td>
                    </tr>
                    <tr>
                        <td align="left" style="border-top: 2px solid rgb(0, 0, 0); padding: 10px 0pt 0pt;">Total:</td>
                        <td style="border-top: 2px solid rgb(0, 0, 0); padding: 10px 0pt 0pt;"><strong>$TotalAmountDollars Currency</strong></td>
                    </tr>
                </tbody>
            </table>
            <p>&nbsp;</p>
            </td>
        </tr>
        <tr>
            <td style="background: none repeat scroll 0% 0% rgb(245, 245, 245); padding-top: 10px;" colspan="2">&nbsp;</td>
        </tr>
    </tbody>
</table>
</div>