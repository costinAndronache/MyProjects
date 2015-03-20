<!DOCTYPE html>
<html>
<head>
<title>Movie catalog report</title>
</head>
<body>
<p>The movies sorted as specified: ${sortingKey} </p></br>

<ul>
<#list categoriesListKey as catElement>
<li>Category name: ${catElement.categoryNameKey}
<ol>
  <#list catElement.movieListKey as movieName>
  <li>${movieName}</li>
  </#list>
</ol> </li>
</#list>
</ul>

</body>
</html>