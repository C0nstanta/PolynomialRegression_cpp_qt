<h1>Multi Polynomial Regression</h1>
<p>This is a multi polynomial regression implemented in C ++.<br />In this version, we set the weights manually.</p>
<p>Normalization is present:</p>
<ul>
<li><strong>Standart Score Normaliztion</strong></li>
<li><strong>Min-Max Normalization</strong></li>
<li><strong>Max Normalization</strong></li>
</ul>
<p>We use <strong>Standart Score Normalization</strong> by default.</p>
<p>We set the degree of our polynomiality by weights.</p>
<p>Degree = Number of scales - 1</p>
<p>That is, if we initialize 5 values of the weights, then we have a polynomial regression of the 4th degree.</p>
<p>Zero weight is used as a free number b(bias) in the equation.</p>
<h2>Y = &Theta;<sub>0</sub> + &Theta;<sub>1</sub> * X + &Theta;<sub>2</sub><sup>2 </sup>* X + &Theta;<span style="font-size: 17.5px;"><sub>3</sub><sup>3</sup> * X + </span>&Theta;<sub>4 </sub><sup>4</sup> * X</h2>
<p>For example, we want to determine the cost of selling an apartment based on the data we have.</p>
<p>Where:</p>
<p><strong>X</strong> - square meters of already sold apartments</p>
<p><strong>Y</strong> - price of apartments sold</p>
<p><strong>alpha</strong> - our learning rate</p>
<p><strong>num_steps</strong> - Number of iterations.</p>
<p><strong>model_weights</strong> - Model weights</p>
<p><strong>square_meters</strong> - Square meters of the apartment for which we want to predict the price</p>
<p><strong>show_every</strong> - show our current prediction every n-iterations</p>
<pre><strong>RESULT:</strong><br />predict_price_denorm: $ 75926<br />predict_price_denorm: $ 86121<br />predict_price_denorm: $ 90246<br />predict_price_denorm: $ 91678<br />predict_price_denorm: $ 92119<br />predict_price_denorm: $ 92220</pre>
<pre><br /><br /><br /></pre>
