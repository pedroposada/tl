<?php 
 /*
  * quieries wrapper
  */
function teligence_purchase_mssqlDbQuery($query = null, $sp_name = null, &$sp_params = array())
{	
	//connection to the database
	if(!function_exists('mssql_connect'))
	{
		watchdog('mssql','Fatal error: Call to undefined function mssql_connect()');
		return false;
	}
	
	if(!$dbhandle = mssql_connect(
		variable_get('teligence_purchase_mssqlServer',""), 
		variable_get('teligence_purchase_mssqlUser',""), 
		variable_get('teligence_purchase_mssqlPass',"")
		))
	{
  		watchdog('mssql',"Couldn't connect to SQL Server on @server", array('@server'=>variable_get('teligence_purchase_mssqlServer', "")));
  		return false;
	}
	
	//select a database to work with
	if(!$selected = mssql_select_db(variable_get('bbm_agent_db_name', ""), $dbhandle))
	{
		watchdog('mssql',"Couldn't open database @db",array('@db'=>$myDB));
		return false;
	}
	  
	// use SQL query
	if(!is_null($query))
	{
		if($result = @mssql_query($query))
		{
			return $result;
		}
		else
		{
			watchdog('mssql',"Invalid SQL: @query",array('@query'=>$query));
			return false;
		}
	}
	
	// use stored procedure
	if(!is_null($sp_name))
	{	
		$proc = mssql_init($sp_name);
		if(count($sp_params) && is_array($sp_params))
		{
			// Bind params to table fields
			foreach((array)$sp_params as $k=>$v)
			{
				mssql_bind($proc, $k,  $v['value'],  $v['type'],  false,  false,  $v['length']);	
			}
		}
		
		// Execute
		try
		{
			$proc_result = @mssql_execute($proc);
			@mssql_free_statement($proc);	
		}
		catch(Exception $e)
		{
			watchdog('mssql','Caught exception: @e',array('@e'=>$e->getMessage()));
			return false;
		}
		return $proc_result;
	}
	else
	{
		watchdog('mssql',"Invalid stored procedure: @sproc",array('@sproc'=>$sp_name));
		return false;
	}
}