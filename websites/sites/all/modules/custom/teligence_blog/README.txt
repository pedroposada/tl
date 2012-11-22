Manual Steps to configure the blog
----------------------------------

1.	Install the teligence_blog module; make sure that neither the core blog nor the advanced_blog modules are installed. This module is currently located in an svn branch at https://192.168.198.173/svn/web/websites/team/pedrop/blog/
2.	Import the content type from  sites/all/modules/teligence_blog/drush/blog.content_type, use the tool from cck module located at  “admin/content/types/import”.
3.	Create two new vocabularies; “Blog Categories” and “Blog Tags”. 
4.	Configure “Blog Categories” for Blog entry content type only; make it required. 
	a.	add at least one term: “Uncategorized”.
5.	Configure “Blog Tags” for Blog entry content type only; not required; check the Tags box.
6.	In admin/build/path/patterns under “Pattern for all Blog entry paths:” put “blog/[title-raw]”.
7.	In admin/build/path/patterns under “Pattern for all Blog Categories paths:” put “blog/category/[tid]”.
8.	In admin/build/path/patterns under “Pattern for all Blog Tags paths:” put “blog/category/[tid]”.
9.	In admin/build/views/import import the view stored at sites/all/module/teligence_blog/drush/archive_blog.view; in the “View name:” field enter “archive_blog” and in the “Paste view code here:” paste the whole script.
10.	Create blog_admin role in admin/user/roles
11.	Set permissions for blog_admin role in admin/user/permissions:
	a.	access blog comment moderation page
	b.	access fckeditor
	c.	create blog content
	d.	delete any blog content
	e.	edit any blog content
	f.	access comments
	g.	administer comments
	h.	post comments
12.	In admin/settings/vppr configure blog_admin to have access to:
	a.	Blog Categories
	b.	Blog Tags
13.	In admin/build/block configure the following blocks to appear in “Right sidebar” region:
	a.	Teligence Blog - Admin Links
	b.	Teligence Blog - Search Form
	c.	Blog - Recent Comments (block)
	d.	Blog - Categories (block)
	e.	Blog - Tags (block)
	f.	Blog - Recent Posts (block)
	g.	Blog - Monthly Archive (block)
14.	Configure each block listed above to show on only the listed pages:
	a.	blog
	b.	blog/*
15.	Configure “Teligence Blog - Admin Links” block to also show on:
	a.	comment/*
	b.	node/add/blog
	c.	admin/content/taxonomy/*
16.	Configure “Teligence Blog - Admin Links” block to show only for role blog_admin
17.	Configure “Teligence Blog - Admin Links” select the categories for Blog Categories and Blog Tags accordingly.
