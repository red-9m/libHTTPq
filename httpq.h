#ifndef _LIBHTTPQ_H_
#define _LIBHTTPQ_H_

extern const int HTTPQ_OK;

enum httpq_retry_policy
{
    rpNoRetry,              // No retry for request
    rpRetryOnTimeoutError   // Retry request on timeout error only (see httpq_set_max_time())
};

/** @brief Initialize HTTPQ library
 *
 *  @return CURL error code
 */
extern long httpq_init();

/** @brief Set URL data
 *
 *         Default value: no value
 *
 *  @param aURL URL string
 *  @return CURL error code
 */
extern long httpq_set_url(const char *aURL);

/** @brief Set POST data. `postData` does not processed with curl_easy_escape()
 *
 *         Default value: no value
 *
 *  @param postData POST data
 *  @return CURL error code
 */
extern long httpq_set_post(const char *postData);

/** @brief Set POST data. Process values with curl_easy_escape(). Keys stay untouched
 *
 *         Default value: no value
 *
 *  @param postData Array of POST key/value
 *                  Ex.: const char *pdata[][2] = {{"key1", "value1"}, {"key2", "value2"}, {NULL, NULL}};
 *                  Array must be ended with {NULL, NULL} element
 *  @return CURL error code
 */
extern long httpq_set_key_post(const char *postData[][2]);

/** @brief Set multipart POST data
 *
 *         Default value: no value
 *
 *  @param postData Array of POST key/value/is_file
 *                  Ex.: const char *pdata[][3] = {{"sender", "John", 0}, {"pic", "/home/john/mypic.jpg", 1}, {NULL, NULL, NULL}};
 *                  Array must be ended with {NULL, NULL, NULL} element
 *                  If element's `is_file` parameter is `1` than passes as post data the contents of the file given in `value`
 *  @return CURL error code
 */
extern long httpq_set_key_http_post(const char *postData[][3]);

/** @brief Set header data
 *
 *         Default value: no value
 *
 *  @param headerData Array of header values
 *                    Ex.: const char *hdata[] = {"header1", "header2", NULL};
 *                    Array must be ended with NULL element
 *  @return CURL error code
 */
extern long httpq_set_headers(const char *headerData[]);

/** @brief Set username
 *
 *         Default value: no value
 *
 *  @param userName Username string
 *  @return CURL error code
 */
extern long httpq_set_user_name(const char *userName);

/** @brief Set user password
 *
 *         Default value: no value
 *
 *  @param userPwd Password string
 *  @return CURL error code
 */
extern long httpq_set_user_pwd(const char *userPwd);

/** @brief Set desired response limit
 *
 *         Response buffer size grows as it receives data from a server
 *         Default value: 4121440 (4Mb)
 *
 *  @param respLimit New response limit in bytes
 *  @return CURL error code
 */
extern long httpq_set_limit_resp(long respLimit);

/** @brief Set maximal time limit for request
 *
 *         Default value: 20 seconds
 *
 *  @param maxTime New time limit for request in seconds. 0 - for unlimited
 *  @return CURL error code
 */
extern long httpq_set_max_time(long maxTime);

/** @brief Set retry policy
 *
 *         Default value: rpRetryOnTimeoutError
 *
 *  @param retryPolicy See enum httpq_retry_policy
 *  @return CURL error code
 */
extern long httpq_set_retry(enum httpq_retry_policy retryPolicy);

/** @brief Make HTTP/HTTPS POST request
 *
 *  @param errorCode Output CURL error code
 *  @param httpCode Output HTTP code (available if errorCode is CURLE_OK)
 *  @return Allocated buffer with HTTP/HTTPS response or NULL in case of error
 *          You must delete buffer later with free()
 */
extern char* httpq_request_post(long* errorCode, long* httpCode);

/** @brief Reset all options that was set by httpq_set_xxx() calls to default
 *
 */
extern void httpq_reset();

/** @brief Converts CURL error code to string
 *
 *  @param errorCode CURL error code
 *  @return Error string
 */
const char* httpq_error(long errorCode);

#endif // _LIBHTTPQ_H_
