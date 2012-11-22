<?php 
 /*
  * quieries wrapper
  */
function bbm_agent_db_query($query = null, $sp_name = null, &$sp_params = array()){
	
	//connection to the database
	if(!function_exists('mssql_connect')):
		drupal_set_message('Fatal error: Call to undefined function mssql_connect()');
		return false;
	endif;
	
	if(!$dbhandle = mssql_connect(
		variable_get('bbm_agent_db_server', ""), 
		variable_get('bbm_agent_db_username', ""), 
		variable_get('bbm_agent_db_pass', "")
		)):
		
  		drupal_set_message("Couldn't connect to SQL Server on " . variable_get('bbm_agent_db_server', ""));
  		return false;
  	endif;
	
	//select a database to work with
	if(!$selected = mssql_select_db(variable_get('bbm_agent_db_name', ""), $dbhandle)):
		drupal_set_message("Couldn't open database $myDB");
		return false;
	endif;
	  
	if(!is_null($query)):
		
		//execute the SQL query and return records
		if($result = @mssql_query($query)):
			return $result;
		else:
			drupal_set_message("Invalid SQL.");
			return false;
		endif;
	endif;
	
	if(!is_null($sp_name)):
		
		// execute the stored procedure
		$proc = mssql_init($sp_name);
		
		if(count($sp_params) && is_array($sp_params))
		{
			// Bind params to table fields
			foreach((array)$sp_params as $param)
			{
				mssql_bind($proc, '@' . $param['name'],  $param['value'],  $param['type'],  false,  false,  $param['length']);	
			}
		}
		
		// Execute
		try
		{
			$proc_result = @mssql_execute($proc);
			
			// only needs to be called if you are worried about using too much memory
			@mssql_free_statement($proc);	
		}
		catch(Exception $e)
		{
			drupal_set_message('Caught exception: ' . $e->getMessage());
			return false;
		}
		
		return $proc_result;
		
	else:
		drupal_set_message("Invalid stored proc.");
		return false;
	endif;
}