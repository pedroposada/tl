<style>
	.ctcCode {
		padding:10px;
		background-color: #F2F2F2;
	}
	.token {
		color: #006106;
		font-weight:bold;
	}
	.demo {
		background-color: #F2F2F2;
		padding:10px;
		border:1px solid #000;
	}
</style>

<h2>Code Snippet</h2>
<pre class="ctcCode">
<?php print $sourceCode ?>
</pre>

<div>
	<div>
	<h2>How it works</h2>
	<ol>
		<li>Copy the code snippet shown above.</li> 
		<li>Find and replace the tokens listed below inside the snippet with your custom values.</li> 
		<li>Provide your client with the modified snippet and have them paste it into their web page.</li> 
		<li>Done.</li> 
	</ol>
	<p>Your clients can style the CTC form using their own css and html. Advice them to not modify the Ids of the original snippet.</p>
	</div>
	
	<h2>Tokens</h2>
	<ul>
		<li class="token">DESTINATIONPHONE</li>
		<li class="token">PARTNERID</li>
		<li class="token">SOURCE</li>
	</ul>
	<p>Each token appears only once.</p>
	
	<h2>Demo</h2>
	<p>Vancouver LLK hub will be used for this demo (DESTINATIONPHONE = 16046383661)</p>
	<div class="demo">
		<?php print str_replace("DESTINATIONPHONE", "16046383661", $demo); ?>
	</div>
</div>