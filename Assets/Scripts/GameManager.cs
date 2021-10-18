using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.Events;
using TMPro;

[DisallowMultipleComponent]
public sealed class GameManager : MonoBehaviour
{
    #region Parameters
    [SerializeField] private TextMeshProUGUI crystalsCountText = null;
    [SerializeField] private TextMeshProUGUI foodCountText = null;

    public UnityEvent LevelFailed;

    private const float standartTimeScale = 1.0f, pauseTimeScale = 0.0f;
    private const int startMinValue = 0;

    private int foodCount, crystalsCount;

    public int FoodCount
    {
        get => foodCount;
        set
        {
            foodCount = value;
            foodCount = Mathf.Clamp(foodCount, startMinValue, int.MaxValue);

            foodCountText.text = $"{foodCount}";
        }
    }

    public int CrystalsCount
    {
        get => crystalsCount;
        set
        {
            crystalsCount = value;
            crystalsCount = Mathf.Clamp(crystalsCount, startMinValue, int.MaxValue);

            crystalsCountText.text = $"{crystalsCount}";
        }
    }
    #endregion

    #region MonoBehaviour API

    private void OnEnable()
    {
        LevelFailed.AddListener(LevelFail);
    }

    private void Start()
    {
        Time.timeScale = standartTimeScale;

        CrystalsCount = FoodCount = startMinValue;
    }

    private void OnDisable()
    {
        LevelFailed.RemoveListener(LevelFail);
    }    
    #endregion

    #region Custom methods
    public void OnFinish()
    {
        Time.timeScale = pauseTimeScale;
    }

    public void LevelFail()
    {
        Time.timeScale = pauseTimeScale;
    }


    public void RestartScene()
    {
        string currentNameOfScene = SceneManager.GetActiveScene().name;

        SceneManager.LoadScene(currentNameOfScene);
    }
    #endregion
}
