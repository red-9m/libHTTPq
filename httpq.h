#ifndef _LIBHTTPQ_H_
#define _LIBHTTPQ_H_

/** @brief Initialize HTTPQ library
 *
 *  @return CURL error code
 */
extern long httpq_init();

/** @brief Set URL data
 *
 *  @param aURL URL string
 *  @return CURL error code
 */
extern long httpq_set_url(const char *aURL);

/** @brief Set POST data
 *
 *  @param postData Two dimensional array of POST key/value
 *                  Ex.: const char *pdata[][2] = {{"key1", "value1"}, {"key2", "value2"}, {NULL, NULL}};
 *                  Array must be ended with {NULL, NULL} element
 *  @return CURL error code
 */
extern long httpq_set_post(const char *postData[][2]);

/** @brief Set multipart POST data
 *
 *  @param postData Two dimensional array of POST key/value/is_file
 *                  Ex.: const char *pdata[][3] = {{"sender", "John", 0}, {"pic", "/home/john/mypic.jpg", 1}, {NULL, NULL, NULL}};
 *                  Array must be ended with {NULL, NULL, NULL} element
 *                  If element's `is_file` parameter is `1` than passes as post data the contents of the file given in `value`
 *  @return CURL error code
 */
extern long httpq_set_httppost(const char *postData[][3]);

/** @brief Set header data
 *
 *  @param headerData Array of header values
 *                    Ex.: const char *hdata[] = {"header1", "header2", NULL};
 *                    Array must be ended with NULL element
 *  @return CURL error code
 */
extern long httpq_set_headers(const char *headerData[]);

/** @brief Set username
 *
 *  @param userName Username string
 *  @return CURL error code
 */
extern long httpq_set_username(const char *userName);

/** @brief Set user password
 *
 *  @param userPwd Password string
 *  @return CURL error code
 */
extern long httpq_set_userpwd(const char *userPwd);

/** @brief Set desired response limit
 *
 *         Response buffer size grows as it receives data from a server
 *         By default limit is set to 4MB to avoid huge memory allocation
 *
 *  @param respLimit New response limit in bytes
 *  @return CURL error code
 */
extern long httpq_set_limit_resp(long respLimit);

/** @brief Set maximal time limit for request
 *
 *         By default time limit is set to 20 seconds
 *
 *  @param maxTime New time limit for request in seconds. 0 - for unlimited
 *  @return CURL error code
 */
extern long httpq_set_maxtime(long maxTime);

/** @brief Make HTTP/HTTPS POST request
 *
 *  @param errorCode Output CURL error code
 *  @param httpCode Output HTTP code (available if errorCode is CURLE_OK)
 *  @return Allocated buffer with HTTP/HTTPS response or NULL in case of error
 *          You must delete buffer later with free()
 */
extern char* httpq_request_post(long* errorCode, long* httpCode);

/** @brief Reset all options that was set by httpq_set_xxx() calls
 *
 */
extern void httpq_reset();

/** @brief Converts CURL error code to string
 *
 *  @param errorCode CURL error code
 *  @return Error string
 */
const char* httpq_error(long errorCode);

#endif
