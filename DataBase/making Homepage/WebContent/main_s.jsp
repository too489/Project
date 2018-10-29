<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <title>Index</title>
  </head>
 
  <style>
      #content {  width: 1300px; margin: 0 auto;  overflow: hidden; }
      #content > #main_section {  width: 750px;  float: left;  }
      #content > #hot_issue { width: 750px; display: inline-block;  }
  </style>
<style media="screen">
.columns  {column-count: 3; border: 0px; column-gap: 0;
display: flex; justify-content: center; align-items: center;}
.columns figure{display: inline-block; border: 0px solid red; margin:10px;}
.columns figure img{width: 100%}
</style>
  <body>
  	<%
		String userID=null;
		if(session.getAttribute("userID")!=null){
		userID=(String)session.getAttribute("userID");
	}
	%>
<nav class="navbar navbar-default">
      <div class="navbar-header">
         <button type="button"class= "navbar-toggle collapsed"
         data-toggle="collapse" data-target="#bs-example-navbar-collapse-1"
         aria-expanded="false">
         <span class="icon-bar"></span>
         <span class="icon-bar"></span>
         <span class="icon-bar"></span>
         </button>
         <a class="navbar-brand" href="main_s.jsp"> KwMain</a>
      </div>
      <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
         <ul class="nav navbar-nav">
            <li><a href="mini_ucam.jsp">Mini_Ucam</a></li>
            <li><a href="kw_bbs.jsp">KW_LIFE</a></li>
         </ul>
           <%
         	if(userID==null){
         %>
         <ul class="nav navbar-nav navbar-right">
            <li class ="dropdown">
               <a href="#" class="dropdown-toggle"
                  data-toggle="dropdown" role = "button" aria-haspopup="true"
                  aria-expanded="false"> 접속하기<span class ="caret"></span></a>
               <ul class="dropdown-menu">
                     <li class="active"><a href="login_s.jsp">로그인</a></li>
                     <li> <a href="join_s.jsp">회원가입</a></li>
                     
              </ul>
            </li>
         </ul>
         <%
         	}else{
         %>
           <ul class="nav navbar-nav navbar-right">
            <li class ="dropdown">
               <a href="#" class="dropdown-toggle"
                  data-toggle="dropdown" role = "button" aria-haspopup="true"
                  aria-expanded="false"> 회원관리<span class ="caret"></span></a>
               <ul class="dropdown-menu">
                     <li><a href="logoutAction.jsp">로그아웃</a></li>             
              </ul>
            </li>
         </ul>
         <%
         }
         %>
      </div>
   </nav>
    <div id="content">
        <section id="main_section">
          <div class ="container">
         <div id="myCarousel" class="carousel slide" data-ride="carousel">
            <ol class="carousel-indicators">
               <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
               <li data-target="#myCarousel" data-slide-to="1"></li>
               <li data-target="#myCarousel" data-slide-to="2"></li>
            </ol>
            <div class="carousel-inner">
               <div class="item active">
                  <img src="images/1.jpg">
               </div>
               <div class="item">
                  <img src="images/2.jpg">
               </div>
               <div class="item">
                  <img src="images/3.jpg">
               </div>
            </div>
         <a class="left carousel-control" href="#myCarousel" data-slide="prev">
            <span class="glyphicon-chevron-left"></span>
         </a>
         <a class="right carousel-control" href="#myCarousel" data-slide="prev">
            <span class="glyphicon-chevron-right"></span>
         </a>
         </div>
   </div>
            <div class="columns">
              <p>  <h1><strong>HOT ISSUE</strong></h1> </p>
                <figure><a href="#">
                  <img src="http://holder.ninja/400x300.svg">
                </a></figure>
                <figure><a href="#">
                  <img src="http://holder.ninja/400x300.svg">
                </a></figure>
                 <figure><a href="#">
                    <img src="http://holder.ninja/400x300.svg">
                  </a></figure>

            </div>
        </section>

  </body>
</html>