package Servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import Database.Insert;
import Database.Select;
import Database.Update;

public class picProcess extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public picProcess() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		request.setCharacterEncoding("utf-8");  
		response.setContentType("text/html;charset=utf-8"); 
        //为解析类提供配置信息  
        DiskFileItemFactory factory = new DiskFileItemFactory();  
        //创建解析类的实例  
        ServletFileUpload sfu = new ServletFileUpload(factory);  
        //开始解析  
        sfu.setFileSizeMax(1600*1600);  
        //每个表单域中数据会封装到一个对应的FileItem对象上  
          

        ServletContext sctx = getServletContext();  
            //获得存放文件的物理路径  
            //upload下的某个文件夹   得到当前在线的用户  找到对应的文件夹  
            String path = sctx.getRealPath("upload");  
            //获得文件名  

            String albumname = request.getParameter("globalalbumname");
            String originphotoname = request.getParameter("originphotoname");
            System.out.println("origin:"+originphotoname);
            String picnum = request.getParameter("picNum");
            
            String photopath = path+"\\"+originphotoname;

        	java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        	java.util.Date currTime = new java.util.Date();
        	String curTime = formatter.format(currTime);
        	String newphotoname = "";
        	com.aviyehuda.easyimage.Image image  = new com.aviyehuda.easyimage.Image(photopath);
            if(picnum.equals("1")){//黑白       		
        		image.convertToBlackAndWhite();            	      		            	
            }else if(picnum.equals("2")){//倾斜
        		image.affineTransform(0.5,0.0);          	
            }else if(picnum.equals("3")){//取中心
        		image.crop(image.getWidth()/5, image.getHeight()/5,4*image.getWidth()/5, 4*image.getHeight()/5);           	
            }else if(picnum.equals("4")){//镜像
        		image.flipHorizontally();         	
            }else if(picnum.equals("5")){//格子图
            	image.multiply(2, 2);
            }else if(picnum.equals("6")){//旋转 左
            	image.rotateLeft();
            }else if(picnum.equals("7")){//旋转 右
            	image.rotateRight();
            }
            newphotoname = curTime+"."+originphotoname.split("\\.")[1];
            newphotoname = newphotoname.replace("-", "");
            newphotoname = newphotoname.replace(" ", "");
            newphotoname = newphotoname.replace(":", "");
            System.out.println("newphotoname:"+newphotoname);
            image.saveAs(path+"\\"+newphotoname);
        	request.getSession().setAttribute("globalalbumname",albumname);
        	request.getSession().setAttribute("globalphotoname",newphotoname);
        	request.getSession().setAttribute("originphotoname",originphotoname);
        	request.getSession().setAttribute("jsporservlet", "servlet");
        	response.sendRedirect("single_pic.jsp");

	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
